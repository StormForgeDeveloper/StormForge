using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

using Sce.Atf.Gui;

namespace SFServerManager
{
    public partial class ServerConfigUploadControl : UserControl
    {
        ServerManagerSetting m_Setting;
        public ServerManagerSetting SettingService {
            get { return m_Setting; }
            set { m_Setting = value; }
        }


        public ServerConfigUploadControl()
        {
            InitializeComponent();
        }


        private void OnLoaded(object sender, EventArgs e)
        {
            listXMLFile.Items.Clear();
            try
            {
                textServerIP.Text = m_Setting.ConnectionString;
                textConfigNodePath.Text = m_Setting.ConfigNodePath;
                textCommandNodePath.Text = m_Setting.CommandNodePath;
                textModulePath.Text = m_Setting.ModulePath;

                for (int i = 0; i < m_Setting.XMLPaths.Count; i++)
                {
                    if (m_Setting.XMLPaths[i] == null)
                        continue;
                    listXMLFile.Items.Add(m_Setting.XMLPaths[i]);// AddRange(m_Setting.XMLPaths.ToArray());                
                }
                if (m_Setting.XMLPaths.Count > 0)
                    listXMLFile.SelectedIndex = 0;
            }
            catch(Exception err)
            {
                MessageBox.Show(err.ToString());
                return;
            }

           
        }


        private void OnXMLSelectionChanged(object sender, EventArgs e)
        {
            var selectedItem = listXMLFile.SelectedValue as string;
            int index = m_Setting.XMLPaths.IndexOf(selectedItem);
            if(index >= 1)
            {
                m_Setting.XMLPaths.Remove(selectedItem);
                m_Setting.XMLPaths.Insert(0, selectedItem);
            }
            else if(index < 0)
            {
                m_Setting.XMLPaths.Insert(0, selectedItem);
            }

            if (m_Setting.XMLPaths.Count > 10)
            {
                m_Setting.XMLPaths.RemoveAt(m_Setting.XMLPaths.Count - 1);
            }
        }


        private void OnXMLEditLeave(object sender, EventArgs e)
        {
            var text = listXMLFile.Text;
            int index = m_Setting.XMLPaths.IndexOf(text);
            if (index >= 0)
                m_Setting.XMLPaths.RemoveAt(index);
            m_Setting.XMLPaths.Insert(0, text);
        }


        private void OnServerIPEditLeave(object sender, EventArgs e)
        {
            var text = textServerIP.Text;
            if (string.IsNullOrEmpty(text))
                return;

            m_Setting.ConnectionString = text;
        }

        private void OnXMLBrowse(object sender, EventArgs e)
        {
            OpenFileDialog openDlg = new OpenFileDialog();
            openDlg.CheckFileExists = true;
            openDlg.Multiselect = false;
            openDlg.DefaultExt = "*.xml";

            if (m_Setting.XMLPaths.Count > 0)
                openDlg.InitialDirectory = Path.GetDirectoryName(m_Setting.XMLPaths[0]);
            else
                openDlg.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            var result = openDlg.ShowDialog();
            if(result == DialogResult.OK)
            {
                var fileName = openDlg.FileName;
                listXMLFile.Text = fileName;
                int index = m_Setting.XMLPaths.IndexOf(fileName);
                if (index >= 0)
                    m_Setting.XMLPaths.RemoveAt(index);
                m_Setting.XMLPaths.Insert(0, fileName);
            }
        }

        private void OnConfigPathChanged(object sender, EventArgs e)
        {
            m_Setting.ConfigNodePath = textConfigNodePath.Text;
        }

        private void OnCommandPathChanged(object sender, EventArgs e)
        {
            m_Setting.CommandNodePath = textCommandNodePath.Text;
        }

        private void OnMoudlePathChanged(object sender, EventArgs e)
        {
            m_Setting.ModulePath = textModulePath.Text;
        }
    }
}

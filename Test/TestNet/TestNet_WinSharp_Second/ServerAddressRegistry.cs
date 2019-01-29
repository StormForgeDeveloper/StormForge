using System;
using System.Windows;
using System.Windows.Controls;
using System.Collections.Generic;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Text;
using System.Runtime.InteropServices;


using SF;
using Microsoft.Win32;

namespace TestNet.WinSharp
{
    partial class ServerAddressRegistry
    {
        static Dictionary<int, List<NetAddress>> m_ServerAddresses = new Dictionary<int, List<NetAddress>>();

        static List<string> m_LoginIDs = new List<string>();

        static readonly int MaxAddresses = 10;
        static readonly string RegistryKeyName = @"SOFTWARE\StormForge\TestNet";

        const int DataTestSize = 1024;

        public static List<string> LoginIDs {  get { return m_LoginIDs; } }

        public static List<NetAddress> GetServerAddresses(int keyIndex)
        {
             if(m_ServerAddresses.ContainsKey(keyIndex))
              return m_ServerAddresses[keyIndex];

            return null;
        }

        public static bool HasAddresses
        {
            get
            {
                if (m_ServerAddresses.Count == 0)
                    return false;

                return true;
            }
        }

        public static bool ReadServerAddress(int KeyIndex)
        {
            if (m_ServerAddresses.ContainsKey(KeyIndex))
                m_ServerAddresses.Remove(KeyIndex);

            bool bRead = false;
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(@"SOFTWARE\StormForge\TestNet"))
            {
                for (int iIP = 0; iIP < MaxAddresses; iIP++)
                {
                    var value = key.GetValue(string.Format("{0}IP{1}", KeyIndex, iIP)) as string;
                    if (string.IsNullOrEmpty(value))
                        break;

                    NetAddress netAddress = new NetAddress();
                    if (!netAddress.Parse(value))
                        continue;

                    if (!m_ServerAddresses.ContainsKey(KeyIndex))
                        m_ServerAddresses.Add(KeyIndex, new List<NetAddress>());

                    m_ServerAddresses[KeyIndex].Add(netAddress);
                    bRead = true;
                }
                key.Close();
            }
            return bRead;
        }

        public static void SaveServerAddressToRegistry()
        {

            foreach(KeyValuePair<int, List<NetAddress>>  Address in m_ServerAddresses)
            {
                if( Address.Value.Count > MaxAddresses)
                    Address.Value.RemoveRange(MaxAddresses, Address.Value.Count - MaxAddresses);

                   using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
                   {
                    int iIP = 0;
                    for (; iIP < Address.Value.Count; iIP++)
                    {
                        var ipAddress = Address.Value[iIP];
                        key.SetValue(  string.Format("{0}IP{1}", Address.Key, iIP), ipAddress.ToString());
                    }

                    for (; iIP < MaxAddresses; iIP++)
                    {
                        try
                        {
                            key.DeleteValue(string.Format("{0}IP{1}", Address.Key, iIP));
                        }
                        catch (Exception)
                        {
                            break;
                        }
                    }
                    key.Close();
                }
            }
        }

        public static bool RemoveServerAddress(int KeyIndex,  NetAddress netAddress)
        {
            if (!m_ServerAddresses.ContainsKey(KeyIndex))
                return false;

            NetAddress FindAddress =
                m_ServerAddresses[KeyIndex].Find(adress => adress.Port == netAddress.Port && adress.Address == netAddress.Address);

            if (!FindAddress.Equals(default(NetAddress)))
            {
                m_ServerAddresses[KeyIndex].Remove(FindAddress);
                return true;
            }

            return false;
        }

        private static bool AddServerAddress(int KeyIndex,  NetAddress netAddress)
        {
            if (!m_ServerAddresses.ContainsKey(KeyIndex))
                m_ServerAddresses.Add(KeyIndex, new List<NetAddress>());

            NetAddress FindAddress =
                m_ServerAddresses[KeyIndex].Find(adress => adress.Port == netAddress.Port && adress.Address == netAddress.Address);

            // If the address not in the address list, add it
            if ( FindAddress.Equals(default(NetAddress)))
            {
                m_ServerAddresses[KeyIndex].Insert(0, netAddress);
                return true;
            }

            return false;
        }

        public static bool AddServerAddress(int KeyIndex, string netAddress)
        {
            NetAddress curSelectedAddress = new NetAddress()
            {
                Address = "127.0.0.1",
                Port = 21001
            };

            if (!string.IsNullOrEmpty(netAddress) && curSelectedAddress.Parse(netAddress))
            {
                //- 삭제.
                RemoveServerAddress(KeyIndex, curSelectedAddress);
                return AddServerAddress(KeyIndex, curSelectedAddress);
            }

            return false;
        }

        //public static bool SelectServerAddress(NetAddress selectedAddress)
        //{
        //    for (int iAddress = 0; iAddress < m_ServerAddresses.Count; iAddress++)
        //    {
        //        if (m_ServerAddresses[iAddress].Equals(selectedAddress))
        //        {
        //            if (iAddress != 0)
        //            {
        //                SelectServerAddress(iAddress);
        //                return true;
        //            }
        //        }
        //    }
        //    return false;
        //}
        //private static void SelectServerAddress(int iIndex)
        //{
        //    var selectedAddress = m_ServerAddresses[iIndex];
        //    m_ServerAddresses.RemoveAt(iIndex);
        //    m_ServerAddresses.Insert(0, selectedAddress);
        //}

        public static void SaveGameID(int Index, string gID)
        {
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                string KeyName = string.Format("GameID_{0}", Index);
                key.SetValue(KeyName, gID.ToString());
                key.Close();
            }
        }

        public static string ReadGameID(int Index, string defaultValue)
        {
            // write down to registry
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                string KeyName = string.Format("GameID_{0}", Index);

                object gameIDString = key.GetValue( KeyName, defaultValue);// m_NetTestUser.m_GameID.ToString());                

                defaultValue = gameIDString.ToString();
            }

            return defaultValue;
        }


        public static bool AddLoginID(string loginID)
        {
            if (m_LoginIDs.IndexOf(loginID) < 0)
            {
                m_LoginIDs.Insert(0, loginID);
                return true;
            }
            return false;
        }

        public static void ReadLoginID()//List<string> LoginIDs)
        {
            m_LoginIDs.Clear();
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                for (int iLogin = 0; iLogin < MaxAddresses; iLogin++)
                {
                    var value = key.GetValue("LoginID" + iLogin) as string;
                    if (string.IsNullOrEmpty(value))
                        break;
                    m_LoginIDs.Add(value);
                }
                key.Close();
            }

        }

        public static void SaveLoginIDFromRegistry()
        {
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                int iLogin = 0;
                for (; iLogin < m_LoginIDs.Count; iLogin++)
                {
                    var loginID = m_LoginIDs[iLogin];
                    key.SetValue("LoginID" + iLogin, loginID);
                }

                for (; iLogin < MaxAddresses; iLogin++)
                {
                    try
                    {
                        key.DeleteValue("LoginID" + iLogin);
                    }
                    catch (Exception)
                    {
                        break;
                    }
                }
                key.Close();
            }
        }


        public static void SaveValue(int Index, string Value)
        {
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                string KeyName = string.Format("CommonValue_{0}", Index);
                key.SetValue(KeyName, Value);
                key.Close();
            }
        }

        public static string ReadValue(int Index, string defaultValue)
        {
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                string KeyName = string.Format("CommonValue_{0}", Index);

                object Value = key.GetValue(KeyName, defaultValue);

                return Value as string;
            }
        }

        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);
        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal,
        int size, string filePath);

        public static bool SetDefaultServerAddress(int KeyIndex, string filePath)
        {
            if (!System.IO.File.Exists(filePath))
                return false;

            StringBuilder DefaultIP = new StringBuilder();
            GetPrivateProfileString("DEFAULT", "IP", "(NONE)", DefaultIP, 32, filePath);
            return AddServerAddress(KeyIndex, DefaultIP.ToString());
        }

        public static bool ReadMaxUser(string filePath, ref int Value)
        {
            if (!System.IO.File.Exists(filePath))
                return false;

            StringBuilder UserCount = new StringBuilder();
            GetPrivateProfileString("MAXUSER", "COUNT", "(NONE)", UserCount, 32, filePath);

            try
            {
                int MaxUserCount = Convert.ToInt32(UserCount.ToString());
                Value = MaxUserCount;
            }
            catch(InvalidCastException e)
            {
                System.Diagnostics.Debug.Print(e.Message);
                return false;
            }

            return true;
        }

        //public static bool ReadReTryIfFailed(string filePath, ref bool Value1, ref bool Value2, ref bool Value3)
        //{
        //    if (!System.IO.File.Exists(filePath))
        //        return false;

        //    StringBuilder DataTestEnable = new StringBuilder();
        //    StringBuilder MatchTestEnable = new StringBuilder();
        //    StringBuilder MatchedChatTestEnable = new StringBuilder();

        //    GetPrivateProfileString("RETRY_IF_FAILED", "DATA_TEST", "(NONE)", DataTestEnable, 32, filePath);
        //    GetPrivateProfileString("RETRY_IF_FAILED", "MATCH_TEST", "(NONE)", MatchTestEnable, 32, filePath);
        //    GetPrivateProfileString("RETRY_IF_FAILED", "MATCHED_CAT_TEST", "(NONE)", MatchedChatTestEnable, 32, filePath);

        //    try
        //    {
        //        Value1  = Convert.ToBoolean(DataTestEnable.ToString());
        //        Value2 = Convert.ToBoolean(MatchTestEnable.ToString());
        //        Value3 = Convert.ToBoolean(MatchedChatTestEnable.ToString());

        //    }
        //    catch (InvalidCastException e)
        //    {
        //        return false;
        //    }

        //    return true;
        //}
    }
}

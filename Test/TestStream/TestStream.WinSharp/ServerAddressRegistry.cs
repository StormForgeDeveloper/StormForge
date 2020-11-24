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

namespace SF
{
    public class ServerAddressRegistry
    {
        static List<string> m_ServerAddresses = new List<string>();

        static readonly int MaxAddresses = 10;
        static readonly string RegistryKeyName = @"SOFTWARE\StormForge\StreamDB";


        public static List<string> GetServerAddresses()
        {
            return m_ServerAddresses;
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

        public static bool ReadServerAddress()
        {
            m_ServerAddresses.Clear();

            bool bRead = false;
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                for (int iIP = 0; iIP < MaxAddresses; iIP++)
                {
                    var value = key.GetValue(string.Format("IP{0}", iIP)) as string;
                    if (string.IsNullOrEmpty(value))
                        break;

                    if (m_ServerAddresses.FindIndex(item => item == value) >= 0)
                        continue;

                    m_ServerAddresses.Add(value);
                    bRead = true;
                }
                key.Close();
            }
            return bRead;
        }

        public static void SaveServerAddressToRegistry()
        {
            if (m_ServerAddresses.Count > MaxAddresses)
                m_ServerAddresses.RemoveRange(MaxAddresses, m_ServerAddresses.Count - MaxAddresses);


            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                int iIP = 0;
                foreach (var address in m_ServerAddresses)
                {
                    key.SetValue(string.Format("IP{0}", iIP), address);
                }
            }
        }

        public static bool RemoveServerAddress(string serverAddress)
        {
            string FindAddress = m_ServerAddresses.Find(adress => adress == serverAddress);

            if (!string.IsNullOrEmpty(FindAddress))
            {
                m_ServerAddresses.Remove(FindAddress);
                return true;
            }

            return false;
        }

        public static bool AddServerAddress(string serverAddress)
        {
            string FindAddress = m_ServerAddresses.Find(adress => adress == serverAddress);

            // If the address not in the address list, add it
            if (string.IsNullOrEmpty(FindAddress))
            {
                m_ServerAddresses.Insert(0, serverAddress);
                return true;
            }

            return false;
        }


    }
}

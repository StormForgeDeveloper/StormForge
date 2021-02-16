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


using Microsoft.Win32;

namespace SF
{
    partial class SavedValueRegistry
    {
        static readonly string RegistryKeyName;

        static SavedValueRegistry()
        {
            var assembly = System.Reflection.Assembly.GetEntryAssembly();
            RegistryKeyName = string.Format(@"SOFTWARE\StormForge\{0}", assembly.GetName().Name);
        }

        public static void SaveValue(string valueName, string value, int index = 0)
        {
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                string KeyName = string.Format("{0}_{1}", valueName, index);
                key.SetValue(KeyName, value);
                key.Close();
            }
        }

        public static string ReadValue(string valueName, string defaultValue, int Index = 0)
        {
            // write down to registry
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey(RegistryKeyName))
            {
                string KeyName = string.Format("{0}_{1}", valueName, Index);

                object gameIDString = key.GetValue( KeyName, defaultValue);
                if (gameIDString != null)
                    defaultValue = gameIDString.ToString();
            }

            return defaultValue;
        }

    }
}

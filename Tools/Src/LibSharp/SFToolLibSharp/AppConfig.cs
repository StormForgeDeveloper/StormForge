////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : application config
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.IO;
using SF;

namespace SF.Tool
{
    public static class AppConfig
    {
        static public ToolSetting ConfigSetting { get; private set; }
        static public ToolSetting ModifiedSetting { get; private set; }
        static public string LocalConfigPath { get; private set; }

        static AppConfig()
        {
            ConfigSetting = new ToolSetting();
            ModifiedSetting = new ToolSetting();
            // Add tool default configurations
            string assemplayName = System.Reflection.Assembly.GetExecutingAssembly().Location;
            string modulePath = Path.GetDirectoryName(assemplayName);

            ConfigSetting.SetValue("ModuleDirectory", modulePath);
            ConfigSetting.SetValue("WorkingDirectory", modulePath);

            SetProjectBasePath(modulePath);

            ConfigSetting.ImportEnvironmentVariables();
            ConfigSetting.ImportParameters();

            string roamingPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData);
            string exeName = Path.GetFileNameWithoutExtension(assemplayName);
            string defaultConfigPath = Path.Combine(modulePath, "0.default_" + exeName + ".cfg");
            if (File.Exists(defaultConfigPath))
            {
                LoadLocalConfig(defaultConfigPath);
            }

            LocalConfigPath = Path.Combine(roamingPath, exeName, exeName + ".cfg");
            LoadLocalConfig(LocalConfigPath);
        }

        static void LoadLocalConfig(string configFilePath)
        {
            ModifiedSetting.LoadLocalConfig(configFilePath);
            foreach (var setting in ModifiedSetting)
            {
                ConfigSetting.SetValue(setting.Key, setting.Value);
            }
        }

        const string PROJECT_ROOT_MARK_FILE = "ProjectRoot.txt";
        static void SetProjectBasePath(string modulePath)
        {
            modulePath = PathTool.NormalizePath(modulePath);
            DirectoryInfo dirInfo = new DirectoryInfo(modulePath);

            while(dirInfo != null)
            {
                var files = dirInfo.GetFiles(PROJECT_ROOT_MARK_FILE);
                if (files != null && files.Length >= 1) break;
                dirInfo = dirInfo.Parent;
            }

            if (dirInfo == null) return;

            ConfigSetting.SetValue("PROJECT_BASE", dirInfo.FullName);
        }

        static public ToolSetting Clone()
        {
            return ConfigSetting.Clone();
        }
        
        
        static public void RemoveValue(string key)
        {
            ConfigSetting.RemoveValue(key);
        }

        static public object GetValue(string key)
        {
            return ConfigSetting.GetValue(key);
        }
        
        static public string GetPath(string keyBasePath, string keyFileName)
        {
            return ConfigSetting.GetPath(keyBasePath, keyFileName);
        }

        static public ReturnType GetValue<ReturnType>(string key, ReturnType defaultValue = default(ReturnType))
        {
            return ConfigSetting.GetValue<ReturnType>(key, defaultValue);
        }

        static public Dictionary<string,object> GetValueSet(string key)
        {
            return ConfigSetting.GetValueSet(key);
        }

        static public string GetValueString(string key, string defaultValue = "")
        {
            return ConfigSetting.GetValueString(key, defaultValue);
        }

        static public int GetValueInt(string key, int defaultValue)
        {
            return ConfigSetting.GetValueInt(key, defaultValue);
        }

        static public float GetValueFloat(string key, float defaultValue)
        {
            return ConfigSetting.GetValueFloat(key, defaultValue);
        }

        // set value
        static public void SetValue(string key, string value)
        {
            ConfigSetting.SetValue(key, value);
            ModifiedSetting.SetValue(key, value);
        }

        // Add value to a value set
        static public void SetValue(string keySet, string key, string value)
        {
            ConfigSetting.SetValue(keySet, key, value);
            ModifiedSetting.SetValue(keySet, key, value);
        }

        static public void SaveLocalConfig()
        {
            ModifiedSetting.SaveLocalConfig(LocalConfigPath);
        }
    }
}

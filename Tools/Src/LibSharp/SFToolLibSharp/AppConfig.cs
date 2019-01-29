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
using System.IO;
using SF;

namespace SF.Tool
{
    public static class AppConfig
    {
        static public ToolSetting ConfigSetting { get; private set; }



        static AppConfig()
        {
            ConfigSetting = new ToolSetting();
            // Add tool default configurations
            string assemplayName = System.Reflection.Assembly.GetExecutingAssembly().Location;
            string modulePath = Path.GetDirectoryName(assemplayName);

            SetValue("ModuleDirectory", modulePath);
            SetValue("WorkingDirectory", modulePath);

            SetProjectBasePath(modulePath);

            ConfigSetting.ImportEnvironmentVariables();
            ConfigSetting.ImportParameters();
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

            ToolDebug.Assert(dirInfo != null);
            if (dirInfo == null) return;

            SetValue("PROJECT_BASE", dirInfo.FullName);
        }

        static public ToolSetting Clone()
        {
            return ConfigSetting.Clone();
        }
        
        
        static public void RemoveValue(string key)
        {
            ConfigSetting.RemoveValue(key);
        }

        static public SettingValue GetValue(string key)
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

        static public SettingValueSet GetValueSet(string key)
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
        }

        // Add value to a value set
        static public void SetValue(string keySet, string key, string value)
        {
            ConfigSetting.SetValue(keySet, key, value);
        }

    }
}

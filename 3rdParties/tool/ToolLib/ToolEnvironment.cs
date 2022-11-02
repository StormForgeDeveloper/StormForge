using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SF.ToolLib
{
    public static class ToolEnvironment
    {
        static Dictionary<string, string> m_Settings = new Dictionary<string, string>();

        static string[] m_EnvironmentSettingNames = new string[]
        {
            "BASE_PATH",
            "DEBUG_TOOLS",
        };



        static ToolEnvironment()
        {
            // apply environment variables
            foreach (var environmentName in m_EnvironmentSettingNames)
            {
                var settingName = Environment.GetEnvironmentVariable(environmentName);
                m_Settings.Add(environmentName, settingName??String.Empty);
            }

            string[] args = Environment.GetCommandLineArgs();
            for (int iArg = 1; iArg < args.Length; iArg++ )
            {
                string argument = args[iArg];
                bool isRemove = argument.StartsWith("-");
                if (isRemove || argument.StartsWith("+"))
                {
                    argument = argument.Substring(1);
                }
                else
                {
                    string? value;
                    if (m_Settings.TryGetValue("", out value))
                        value += ",";
                    else
                        value = String.Empty;
                    value += argument;
                    m_Settings["UNNAMED"] = value;
                }

                if (string.IsNullOrEmpty(argument))
                {
                    continue;
                }

                string argumentValue = "";
                int splitIndex = argument.IndexOf(':');
                if (splitIndex < 0)
                {
                    argumentValue = "true";
                }
                else
                {
                    argumentValue = argument.Substring(splitIndex + 1);
                    argument = argument.Substring(0, splitIndex);
                }

                if (isRemove)
                {
                    m_Settings.Remove(argument);
                }
                else
                {
                    m_Settings.Add(argument, argumentValue);
                }
            }


        }

        public static string GetSettingString(string key, string defaultValue = "")
        {
            string? stringValue;
            if (!m_Settings.TryGetValue(key, out stringValue))
                stringValue = defaultValue;
            return stringValue;
        }

        public static T? GetSetting<T>(string key, T? defaultValue = default(T))
        {
            string? stringValue;
            if(!m_Settings.TryGetValue(key, out stringValue))
            {
                stringValue = String.Empty;
            }

            T? resultValue = defaultValue;
            try
            {
                if (!string.IsNullOrEmpty(stringValue))
                    resultValue = (T)Convert.ChangeType(stringValue, typeof(T));
            }
            catch(Exception)
            {
                resultValue = defaultValue;
            }

            return resultValue;
        }



        public static void CheckDebugOption(string toolName)
        {
            toolName = toolName.ToLower();
            string debugTools = GetSettingString("DEBUG_TOOLS");
            if (!string.IsNullOrEmpty(debugTools))
            {
                foreach (var debugTool in debugTools.Split(','))
                {
                    if (debugTool.ToLower() == toolName)
                    {
                        System.Diagnostics.Debug.Assert(false);
                        return;
                    }
                }
            }
        }
    }
}

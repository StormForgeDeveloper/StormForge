////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Tool setting
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SF.Tool
{
    [Export(typeof(ToolSetting))]
    public class ToolSetting
    {
        Dictionary<string, SettingValue> m_Configurations = new Dictionary<string, SettingValue>();

        [ImportingConstructor]
        public ToolSetting()
        {
        }

        public ToolSetting Clone()
        {
            ToolSetting newSetting = new ToolSetting();
            foreach (var config in m_Configurations)
            {
                var clone = config.Value.Clone();
                newSetting.m_Configurations.Add(config.Key, clone);
            }

            return newSetting;
        }

        public void ParseArgument(string argument)
        {
            if (string.IsNullOrEmpty(argument)) return;

            bool isAdd = true;
            if (argument.StartsWith("-"))
            {
                argument = argument.Substring(1);
                isAdd = false;
            }
            else if(argument.StartsWith("+"))
            {
                argument = argument.Substring(1);
                isAdd = true;
            }

            int valueStart = argument.IndexOf('=');
            string key;
            string value;
            if(valueStart >= 0)
            {
                key = argument.Substring(0, valueStart);
                value = argument.Substring(valueStart + 1);
            }
            else
            {
                key = argument;
                value = "";
            }
            string[] values = value.Split(';');

            if (!isAdd)
            {
                foreach(var newValue in values)
                {
                    if (string.IsNullOrEmpty(newValue)) continue;

                    // remove value
                    var settingValue = GetValue(key);
                    if (settingValue == null) break;
                    if (settingValue is SettingValueSet)
                    {
                        ((SettingValueSet)settingValue).RemoveValue(newValue);
                    }
                    else
                    {
                        RemoveValue(key);
                    }
                }
            }
            else
            {
                foreach (var newValue in values)
                {
                    if (string.IsNullOrEmpty(newValue)) continue;

                    var keyValue = GetValue(key);
                    if (keyValue is SettingValueString)
                    {
                        var strValue = keyValue as SettingValueString;
                        RemoveValue(strValue.Key);
                        SetValue(strValue.Key, strValue.Value, "");
                        keyValue = null;
                    }

                    if (keyValue == null)
                    {
                        if (values.Length > 1)
                            SetValue(key, newValue, newValue);
                        else
                            SetValue(key, newValue);
                    }
                    else
                    {
                        SettingValueSet keyValueSet = keyValue as SettingValueSet;
                        keyValueSet.SetValue(newValue, newValue);
                    }
                }
            }
        }

        //static string[] stm_ImportEnvironmentVariableNames = {
        //    "DEFINES",
        //    "INCLUDE",
        //    "PLATFORM",
        //    "CONFIGURATION",
        //    "OBJ_PATH",
        //    "OUTPUT_PATH",
        //    "TOOL_DEBUG"
        //};
        public void ImportEnvironmentVariables()
        {
            var envVars = Environment.GetEnvironmentVariables();

            //string pathVarName = null;
            //foreach (string envVarKey in envVars.Keys)
            //{
            //    if(envVarKey.ToLower() == "path")
            //    {
            //        pathVarName = envVarKey;
            //        break;
            //    }
            //}

            //// VS version path detect
            //List<Version> vsVersions = new List<Version>() { new Version("14.0"), new Version("12.0") };
            //foreach (var vcVersion in vsVersions)
            //{
            //    var vcVarName = string.Format("VS{0}{1}COMNTOOLS", vcVersion.Major, vcVersion.Minor);
            //    if (!envVars.Contains(vcVarName)) continue;
            //    var vsPathCommon = envVars[vcVarName] as string;
            //    if (string.IsNullOrEmpty(vsPathCommon)) continue;

            //    SetValue("VSCOMNTOOLS", vsPathCommon);
            //    var vsPathCommon2 = Path.GetFullPath(Path.Combine(vsPathCommon, @"..\"));
            //    var vsBasePath = Path.GetFullPath(Path.Combine(vsPathCommon, @"..\..\"));
            //    SetValue("VS_PATH", vsBasePath);

            //    var path = envVars[pathVarName];
            //    var vsBinPath = Path.Combine(vsBasePath, @"VC\bin");
            //    var vsBinPath2 = Path.Combine(vsBasePath, @"VC\bin\x86_amd64");
            //    var vsBinPath3 = Path.Combine(vsBasePath, @"VC");
            //    path = vsBinPath + ";" + vsBinPath2 + ";" + vsPathCommon + ";" + vsPathCommon2 + ";" +path;
            //    envVars[pathVarName] = path;
            //    break;
            //}

            //foreach (var envVarName in stm_ImportEnvironmentVariableNames)
            foreach (string envVarName in envVars.Keys)
            {
                //if (!envVars.Contains(envVarName)) continue;

                var varString = envVars[envVarName] as string;
                if (string.IsNullOrEmpty(varString)) continue;
                var varStrings = varString.Split(';');

                if(varStrings.Length > 1)
                {
                    foreach (var varValue in varStrings)
                    {
                        if (string.IsNullOrEmpty(varValue)) continue;

                        SetValue(envVarName, varValue, "");
                    }
                }
                else
                {
                    SetValue(envVarName, varStrings[0]);
                }
            }
            
        }


        public void ImportParameters()
        {
            string[] args = Environment.GetCommandLineArgs();
            for (int iArg = 1; iArg < args.Length; iArg++)
            {
                string argument = args[iArg];
                ParseArgument(argument);
            }
        }
        
        #region Enumerator implementation
        public class Enumerator : IEnumerator<SettingValue>
        {
            Dictionary<string, SettingValue> m_Map;
            Dictionary<string, SettingValue>.Enumerator m_Enumerator;

            public Enumerator(Dictionary<string, SettingValue> values)
            {
                m_Map = values;
                m_Enumerator = m_Map.GetEnumerator();
            }

            public void Dispose()
            {
            }

            public bool MoveNext() { return m_Enumerator.MoveNext(); }
            public void Reset() { m_Enumerator = m_Map.GetEnumerator(); }

            public SettingValue Current { get { return m_Enumerator.Current.Value; } }
            object IEnumerator.Current { get { return m_Enumerator.Current.Value; } }
        }

        //IEnumerator IEnumerable.GetEnumerator() { return new Enumerator(m_Configurations); }

        public IEnumerator<SettingValue> GetEnumerator() { return new Enumerator(m_Configurations); }

        #endregion Enumerator

        public void RemoveValue(string key)
        {
            //if (m_Configurations.ContainsKey(key))
            m_Configurations.Remove(key);
        }

        public SettingValue GetValue(string key)
        {
            SettingValue value;
            m_Configurations.TryGetValue(key.ToLower(), out value);
            return value;
        }

        /// <summary>
        /// Get path setting
        /// </summary>
        /// <param name="keyBasePath"></param>
        /// <param name="keyFileName"></param>
        /// <returns></returns>
        public string GetPath(string keyBasePath, string keyFileName)
        {
            return PathTool.CombinePath(GetValue<string>(keyBasePath), GetValue<string>(keyFileName));
        }
        public ReturnType GetValue<ReturnType>(string key, ReturnType defaultValue = default(ReturnType))
        {
            var valueString = GetValueString(key);
            if (string.IsNullOrEmpty(valueString)) return defaultValue;
            var returnType = typeof(ReturnType);
            if (returnType.IsEnum)
            {
                foreach(var value in returnType.GetEnumValues())
                {
                    if(returnType.GetEnumName(value).ToLower() == valueString.ToLower())
                    {
                        return (ReturnType)value;
                    }
                }
                throw new InvalidCastException(valueString);
            }
            else
                return (ReturnType)Convert.ChangeType((object)valueString, typeof(ReturnType));
        }

        public SettingValueSet GetValueSet(string key)
        {
            SettingValue value;
            key = key.ToLower();
            if (m_Configurations.TryGetValue(key.ToLower(), out value))
            {
                var valueSet = value as SettingValueSet;
                if (valueSet != null) return valueSet;

                // wrap the value as value set
                valueSet = new SettingValueSet(key.ToLower());
                valueSet.SetValue((value as SettingValueString).Value, "");
                return valueSet;
            }
            return null;
        }

        public string GetValueString(string key, string defaultValue = "")
        {
            SettingValue value;
            key = key.ToLower();
            if (!m_Configurations.TryGetValue(key.ToLower(), out value)) return defaultValue;
            var stringValue = value as SettingValueString;
            if (stringValue == null) return defaultValue;

            return stringValue.Value;
        }

        public int GetValueInt(string key, int defaultValue)
        {
            SettingValue value;
            key = key.ToLower();
            if (!m_Configurations.TryGetValue(key.ToLower(), out value)) return defaultValue;
            var stringValue = value as SettingValueString;
            if (stringValue == null) return defaultValue;

            int result;
            if (!int.TryParse(stringValue.Value, out result)) return defaultValue;

            return result;
        }

        public float GetValueFloat(string key, float defaultValue)
        {
            SettingValue value;
            key = key.ToLower();
            if (!m_Configurations.TryGetValue(key.ToLower(), out value)) return defaultValue;
            var stringValue = value as SettingValueString;
            if (stringValue == null) return defaultValue;

            float result;
            if (!float.TryParse(stringValue.Value, out result)) return defaultValue;

            return result;
        }

        // set value
        public void SetValue(string key, string value)
        {
            string keyLwr = key.ToLower();
            var keyValue = GetValue(keyLwr);
            if (keyValue == null)
            {
                m_Configurations.Add(keyLwr, new SettingValueString(keyLwr, value));
            }
            else if (keyValue is SettingValueSet)
            {
                var valueSet = (SettingValueSet)keyValue;
                valueSet.SetValue(value, value);
            }
            else if(keyValue is SettingValueString)
            {
                var valueString = (SettingValueString)keyValue;
                valueString.Value = value;
            }
            else
            {
                ToolDebug.Error("Key type not match for key:{0}, value:{1}", key, value);
            }
        }

        // Add value to a value set
        public void SetValue(string keySet, string key, string value)
        {
            string keySetLwr = keySet.ToLower();
            var keyValue = GetValue(keySetLwr);
            if (keyValue == null)
            {
                keyValue = new SettingValueSet(keySetLwr);
                m_Configurations.Add(keySetLwr, keyValue);
            }

            if (keyValue is SettingValueSet)
            {
                var valueSet = (SettingValueSet)keyValue;
                valueSet.SetValue(key, value);
            }
            else
            {
                ToolDebug.Error("Key type not match for key:{0}, value:{1}", key, value);
            }
        }

    }
}

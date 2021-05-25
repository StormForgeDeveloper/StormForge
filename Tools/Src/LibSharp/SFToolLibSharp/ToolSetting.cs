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
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace SF.Tool
{
    public class ToolSetting
    {
        Dictionary<string, object> m_Configurations = new Dictionary<string, object>();

        public ToolSetting()
        {
        }

        public ToolSetting Clone()
        {
            ToolSetting newSetting = new ToolSetting();
            foreach (var config in m_Configurations)
            {
                var valueSet = config.Value as Dictionary<string, object>;
                if (valueSet != null)
                {
                    var newValueSet = new Dictionary<string, object>(valueSet);
                    newSetting.m_Configurations.Add(config.Key, newValueSet);
                }
                else
                {
                    newSetting.m_Configurations.Add(config.Key, config.Value);
                }
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
                    var settingSet = settingValue as Dictionary<string, object>;
                    if (settingSet != null)
                    {
                        settingSet.Remove(newValue);
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
                    if (keyValue is string)
                    {
                        var strValue = keyValue as string;
                        RemoveValue(key);
                        SetValue(key, strValue, "");
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
                        Dictionary<string,object> keyValueSet = keyValue as Dictionary<string,object>;
                        keyValueSet[newValue] = newValue;
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


        #region Json config


        object JsonElementToObject(JsonElement jsonValue)
        {
            switch (jsonValue.ValueKind)
            {
                case JsonValueKind.String:
                    return jsonValue.GetString();
                case JsonValueKind.Object:
                    var newDic = new Dictionary<string, object>();
                    foreach (var itObj in jsonValue.EnumerateObject())
                    {
                        newDic[itObj.Name] = JsonElementToObject(itObj.Value);
                    }
                    return newDic;
                case JsonValueKind.Array:
                    return jsonValue;
                case JsonValueKind.Number:
                    return jsonValue.GetDouble();
                default:
                    return null;
            }
        }

        public void LoadLocalConfig(string configPath)
        {
            if (!File.Exists(configPath))
                return;

            var jsonData = File.ReadAllText(configPath, Encoding.UTF8);
            var loadedDictionary = JsonSerializer.Deserialize<Dictionary<string, object>>(jsonData);
            if (loadedDictionary == null)
                return;


            foreach (var setting in loadedDictionary)
            {
                var valueObj = setting.Value;
                if (valueObj.GetType() == typeof(JsonElement))
                {
                    var jsonValue = (JsonElement)valueObj;
                    SetValue(setting.Key, JsonElementToObject(jsonValue));
                }
                else
                {
                    SetValue(setting.Key, valueObj);
                }
            }
        }
        public void SaveLocalConfig(string configPath)
        {
            JsonSerializerOptions options = new JsonSerializerOptions() { WriteIndented = true };
            var jsonData = JsonSerializer.Serialize(m_Configurations, options: options);
            var dirPath = Path.GetDirectoryName(configPath);
            if (!Directory.Exists(dirPath))
                Directory.CreateDirectory(dirPath);

            File.WriteAllText(configPath, jsonData, Encoding.UTF8);
        }
        #endregion

        #region Enumerator implementation
        
        //IEnumerator IEnumerable.GetEnumerator() { return new Enumerator(m_Configurations); }

        public Dictionary<string, object>.Enumerator GetEnumerator() { return m_Configurations.GetEnumerator(); }

        #endregion Enumerator

        public void RemoveValue(string key)
        {
            //if (m_Configurations.ContainsKey(key))
            m_Configurations.Remove(key);
        }

        public object GetValue(string key)
        {
            object value;
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

        public Dictionary<string,object> GetValueSet(string key)
        {
            object value;
            key = key.ToLower();
            if (m_Configurations.TryGetValue(key.ToLower(), out value))
            {
                var valueSet = value as Dictionary<string,object>;
                if (valueSet != null) return valueSet;

                // wrap the value as value set
                valueSet = new Dictionary<string,object>();
                valueSet[value as string] = value;
                return valueSet;
            }
            return null;
        }

        public string GetValueString(string key, string defaultValue = "")
        {
            object value;
            key = key.ToLower();
            if (!m_Configurations.TryGetValue(key.ToLower(), out value)) return defaultValue;
            var stringValue = value as string;
            if (stringValue == null) return defaultValue;

            return stringValue;
        }

        public int GetValueInt(string key, int defaultValue)
        {
            object value;
            key = key.ToLower();
            if (!m_Configurations.TryGetValue(key.ToLower(), out value)) return defaultValue;
            var stringValue = value as string;
            if (stringValue == null) return defaultValue;

            int result;
            if (!int.TryParse(stringValue, out result)) return defaultValue;

            return result;
        }

        public float GetValueFloat(string key, float defaultValue)
        {
            object value;
            key = key.ToLower();
            if (!m_Configurations.TryGetValue(key.ToLower(), out value)) return defaultValue;
            var stringValue = value as string;
            if (stringValue == null) return defaultValue;

            float result;
            if (!float.TryParse(stringValue, out result)) return defaultValue;

            return result;
        }

        // set value
        public void SetValue(string key, string value)
        {
            string keyLwr = key.ToLower();
            var keyValue = GetValue(keyLwr);
            if (keyValue == null)
            {
                m_Configurations.Add(keyLwr, value);
            }
            else if (keyValue is Dictionary<string,object>)
            {
                var valueSet = (Dictionary<string,object>)keyValue;
                valueSet[value] = value;
            }
            else if(keyValue is string)
            {
                m_Configurations[keyLwr] = value;
            }
            else
            {
                ToolDebug.Error("Key type not match for key:{0}, value:{1}", key, value);
            }
        }

        // set value
        public void SetValue(string key, object value)
        {
            string keyLwr = key.ToLower();
            var keyValue = GetValue(keyLwr);
            if (keyValue == null)
            {
                m_Configurations.Add(keyLwr, value);
            }
            else
            {
                m_Configurations[keyLwr] = value;
            }
        }

        // Add value to a value set
        public void SetValue(string keySet, string key, string value)
        {
            string keySetLwr = keySet.ToLower();
            var keyValue = GetValue(keySetLwr);
            if (keyValue == null)
            {
                keyValue = new Dictionary<string,object>();
                m_Configurations.Add(keySetLwr, keyValue);
            }

            var valueSet = keyValue as Dictionary<string, object>;
            if (valueSet != null)
            {
                valueSet[key] = value;
            }
            else
            {
                var newkeyValue = new Dictionary<string, object>();
                newkeyValue[keyValue as string] = "";
                newkeyValue[key] = "";
                m_Configurations[keySetLwr] = newkeyValue;
            }
        }

    }
}

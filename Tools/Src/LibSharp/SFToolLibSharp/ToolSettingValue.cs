////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : tool setting value
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace SF.Tool
{
    public abstract class SettingValue
    {
        public string Key { get; protected set; }

        public abstract SettingValue Clone();

        protected void CopyValues(SettingValue newItem)
        {
            newItem.Key = Key;
        }
    }

    public class SettingValueString : SettingValue
    {
        public string Value { get; set; }

        public SettingValueString() { }

        public SettingValueString(string key, string value)
        {
            Key = key;
            Value = value;
        }

        public override SettingValue Clone()
        {
            var newItem = new SettingValueString();
            base.CopyValues(newItem);
            newItem.Value = Value;
            ToolDebug.Assert(newItem.Key == Key);
            return newItem;
        }
    }

    public class SettingValueSet : SettingValue, IEnumerable<SettingValueString>
    {
        Dictionary<string, SettingValueString> Values = new Dictionary<string, SettingValueString>();

        public SettingValueSet()
        {
        }

        public SettingValueSet(string key)
        {
            Key = key;
        }

        public override SettingValue Clone()
        {
            var newItem = new SettingValueSet();
            base.CopyValues(newItem);

            foreach (var val in Values)
            {
                var newValue = val.Value.Clone() as SettingValueString;
                ToolDebug.Assert(newValue.Key == val.Key);
                newItem.Values.Add(val.Key, newValue);
            }

            return newItem;
        }

        #region Enumerator implementation
        public class Enumerator : IEnumerator<SettingValueString>
        {
            Dictionary<string, SettingValueString> m_Map;
            Dictionary<string, SettingValueString>.Enumerator m_Enumerator;

            public Enumerator(Dictionary<string, SettingValueString> values)
            {
                m_Map = values;
                m_Enumerator = m_Map.GetEnumerator();
            }

            public void Dispose()
            {
            }

            public bool MoveNext() { return m_Enumerator.MoveNext(); }
            public void Reset() { m_Enumerator = m_Map.GetEnumerator(); }

            public SettingValueString Current { get { return m_Enumerator.Current.Value; } }
            object IEnumerator.Current { get { return m_Enumerator.Current.Value; } }
        }

        IEnumerator IEnumerable.GetEnumerator() { return new Enumerator(Values); }

        public IEnumerator<SettingValueString> GetEnumerator() { return new Enumerator(Values); }

        #endregion Enumerator

        public void RemoveValue(string key)
        {
            Values.Remove(key);
        }

        public SettingValueString GetValue(string key)
        {
            SettingValueString value;
            Values.TryGetValue(key, out value);
            return value;
        }

        public void SetValue(string key, string value)
        {
            var keyValue = GetValue(key);
            if(keyValue == null)
            {
                Values.Add(key, new SettingValueString(key, value));
            }
            else
            {
                keyValue.Value = value;
            }
        }

    }
}

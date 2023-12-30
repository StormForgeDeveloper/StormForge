////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;

#nullable enable

namespace SF
{

    public class SFMessage : SFObject
    {
        int m_MessageID;

        Dictionary<string, Object?> m_Values = new ();

        public SFMessage(int messageID)
        {
            m_MessageID = messageID;
        }

        public SFMessage()
        {
            m_MessageID = 0;
        }

        public int GetMessageID()
        {
            return m_MessageID;
        }

        public Object? GetValue(string valueName)
        {
            return m_Values[valueName];
        }

        public bool TryGetValue<ValueType>(string valueName, out ValueType? outValue)
        {
            outValue = default(ValueType);
            object? value = null;
            if (!m_Values.TryGetValue(valueName, out value))
            {
                return false;
            }

            if (value == null)
            {
                // null value is legit default
                outValue = default(ValueType);
                return true;
            }

            if (value.GetType() == typeof(ValueType))
            {
                outValue = (ValueType)value;
                return true;
            }
            else
            {
                var requestedType = typeof(ValueType);
                if (requestedType.IsEnum)
                {
                    var intValue = (int)System.Convert.ChangeType(value, typeof(int));
                    var values = Enum.GetValues(requestedType);
                    foreach (object enumValue in values)
                    {
                        if ((int)enumValue == intValue)
                        {
                            outValue = (ValueType)value;
                            return true;
                        }
                    }
                    throw new Exception("Can't cast the value");
                }
                else
                {
                    outValue = (ValueType)System.Convert.ChangeType(value, typeof(ValueType));
                    return true;
                }
            }
        }

        public ValueType? GetValue<ValueType>(string valueName)
        {
            ValueType? outValue;

            TryGetValue(valueName, out outValue);

            return outValue;
        }

        public void SetValue(string valueName, Object? value)
        {
            m_Values.Add(valueName, value);
        }

        public Dictionary<string, Object?> GetValues()
        {
            return m_Values;
        }
    }
}

#nullable restore

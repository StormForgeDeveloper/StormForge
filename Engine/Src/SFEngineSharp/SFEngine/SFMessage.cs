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


namespace SF
{



    public class SFMessage : SFObject
    {
        int m_MessageID;

        Dictionary<string, Object> m_Values = new Dictionary<string, Object>();

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

        public Object GetValue(string valueName)
        {
            return m_Values[valueName];
        }

        public ValueType GetValue<ValueType>(string valueName)
        {
            object value;
            if(!m_Values.TryGetValue(valueName,out value))
            {
                return default(ValueType);
            }

            if (value.GetType() == typeof(ValueType))
                return (ValueType)value;
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
                            return (ValueType)enumValue;
                    }
                    throw new Exception("Can't cast the value");
                }
                else
                    return (ValueType)System.Convert.ChangeType(value, typeof(ValueType));
            }
        }

        public void SetValue(string valueName, Object value)
        {
            m_Values.Add(valueName, value);
        }

        public Dictionary<string, Object> GetValues()
        {
            return m_Values;
        }
    }
}


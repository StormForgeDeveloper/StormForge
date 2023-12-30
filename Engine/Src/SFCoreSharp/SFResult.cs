////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Result code
//	
//
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Collections.Generic;
using System.Reflection;

#nullable enable

namespace SF {
	public struct Result
    {
        #region Static result code table

        static Dictionary<int, string> stm_ResultCodeTable;

        static Result()
        {
            stm_ResultCodeTable = new Dictionary<int, string>();

            var resultCodeType = typeof(ResultCode);
            var fields = resultCodeType.GetFields(BindingFlags.Public | BindingFlags.Static );
            foreach (var field in fields)
            {
                if (field.FieldType != typeof(int))
                    continue;

                var errorCode = (int)(field.GetValue(null) ?? 0);
                var errorName = field.Name;
                stm_ResultCodeTable.Add(errorCode, errorName);
            }

        }
        #endregion

        public int Code;

        public Result(int code)
        {
            Code = code;
        }

        public Result(Result src)
        {
            Code = src.Code;
        }

        public bool IsFailure { get { return Code < 0; } }

        public bool IsSucceeded { get { return Code >= 0; } }

        public override string ToString()
        {
            string? strValue;
            if (!stm_ResultCodeTable.TryGetValue(Code, out strValue))
                strValue = string.Format("{0:X8}", Code);
            return strValue;
        }


        public override int GetHashCode()
        {
            return Code;
        }

        public override bool Equals(System.Object? obj)
        {
            // If parameter is null return false.
            if (obj == null)
            {
                return false;
            }

            // If parameter cannot be cast to Point return false.
            Result p = (Result)obj;

            return Code == p.Code;
        }

        public bool Equals(Result p)
        {
            return Code == p.Code;
        }

        public static bool operator ==(Result a, Result b)
        {
            return a.Code == b.Code;
        }

        public static bool operator !=(Result a, Result b)
        {
            return a.Code != b.Code;
        }

        public static bool operator ==(Result a, Int32 b)
        {
            return a.Code == b;
        }

        public static bool operator !=(Result a, Int32 b)
        {
            return a.Code != b;
        }
    }


}

#nullable restore

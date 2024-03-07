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
        #region Constants

        static readonly int CodeBits = 16;
        static readonly int CodeMask = (1 << CodeBits) - 1;
        static readonly int CodeShift = 0;

        static readonly int FacilityBits = 12;
        static readonly int FacilityMask = (1 << FacilityBits) - 1;
        static readonly int FacilityShift = (CodeBits + CodeShift);

        static readonly int ReservedBits = 1;
        static readonly int ReservedMask = (1 << ReservedBits) - 1;
        static readonly int ReserveShift = (FacilityBits + FacilityShift);

        static readonly int CustomBits = 1;
        static readonly int CustomMask = (1 << CustomBits) - 1;
        static readonly int CustomShift = (ReservedBits + ReserveShift);

        static readonly int SeverityBits = 2;
        static readonly int SeverityMask = (1 << SeverityBits) - 1;
        static readonly int SeverityShift = (CustomBits + CustomShift);

        #endregion

        public enum SeverityType
        {
            Success,
            Informational,
            Warning,
            Error
        };

        public static string ServerityToDefineString(SeverityType serverity)
        {
            switch (serverity)
            {
                case SeverityType.Success: return "SUCCESS_";
                case SeverityType.Informational: return "I_";
                case SeverityType.Warning: return "W_";
                case SeverityType.Error:
                default:
                    return "";
            }
        }


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


        public SeverityType Severity
        {
            get { return (SeverityType)((Code >> SeverityShift) & SeverityMask); }
            set { Code = (Code & (~(SeverityMask << SeverityShift))) | (((int)value & SeverityMask) << SeverityShift); }
        }

        public bool Custom
        {
            get { return ((Code >> CustomShift) & CustomMask) != 0; }
            set { Code = (Code & (~(CustomMask << CustomShift))) | (((value ? 1 : 0) & CustomMask) << CustomShift); }
        }

        public int Facility
        {
            get { return (Code >> FacilityShift) & FacilityMask; }
            set { Code = (Code & (~(FacilityMask << FacilityShift))) | ((value & FacilityMask) << FacilityShift); }
        }

        public int CodeIndex
        {
            get { return (Code >> CodeShift) & CodeMask; }
            set { Code = (Code & (~(CodeMask << CodeShift))) | ((value & CodeMask) << CodeShift); }
        }
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

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : 
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SF
{
    public partial struct ResultCode
    {
        #region Constants

        const int CodeBits = 16;
        const int CodeMask = (1 << CodeBits) - 1;
        const int CodeShift = 0;

        const int FacilityBits = 12;
        const int FacilityMask = (1 << FacilityBits) - 1;
        const int FacilityShift = (CodeBits + CodeShift);

        const int ReservedBits = 1;
        const int ReservedMask = (1 << ReservedBits) - 1;
        const int ReserveShift = (FacilityBits + FacilityShift);

        const int CustomBits = 1;
        const int CustomMask = (1 << CustomBits) - 1;
        const int CustomShift = (ReservedBits + ReserveShift);

        const int SeverityBits = 2;
        const int SeverityMask = (1 << SeverityBits) - 1;
        const int SeverityShift = (CustomBits + CustomShift);

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

        public static bool IsSuccessed(Int32 resCode) { return resCode >= 0; }
        public static bool IsFailed(Int32 resCode) { return resCode < 0; }


        public Int32 ID;

        public ResultCode(Int32 inID)
        {
            ID = inID;
        }

        public ResultCode(UInt32 inID)
        {
            ID = (int)inID;
        }

        public ResultCode(SeverityType severity, bool custom, int facility, int code)
        {
            ID = 0;
            Severity = severity;
            Custom = custom;
            Facility = facility;
            Code = code;
        }

        public bool IsSuccessed() { return IsSuccessed(ID); }
        public bool IsFailed() { return IsFailed(ID); }


        public SeverityType Severity
        {
            get { return (SeverityType)((ID >> SeverityShift) & SeverityMask); }
            set { ID = (ID & (~(SeverityMask << SeverityShift))) | (((int)value & SeverityMask) << SeverityShift); }
        }

        public bool Custom
        {
            get { return ((ID >> CustomShift) & CustomMask) != 0; }
            set { ID = (ID & (~(CustomMask << CustomShift))) | (((value?1:0) & CustomMask) << CustomShift); }
        }

        public int Facility
        {
            get { return (ID >> FacilityShift) & FacilityMask; }
            set { ID = (ID & (~(FacilityMask << FacilityShift))) | ((value & FacilityMask) << FacilityShift); }
        }

        public int Code
        {
            get { return (ID >> CodeShift) & CodeMask; }
            set { ID = (ID & (~(CodeMask << CodeShift))) | ((value & CodeMask) << CodeShift); }
        }
    }
}

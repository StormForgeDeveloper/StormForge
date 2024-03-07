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
using System.IO;
using System.Xml.Serialization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.Table;


namespace SF.Table
{
    public partial class ResultCodes
    {
        public int FacilityCode;
    }
}


namespace SF
{

    public class ResultCodeProcessor
    {
        Dictionary<string, ResultCodeFacility> m_Facilities = new Dictionary<string, ResultCodeFacility>();
        ResultCodes m_Codes;

        public void LoadFacility(string facilitiyPath)
        {
            ResultCodeFacilities facilities;
            XmlSerializer serializer = new XmlSerializer(typeof(ResultCodeFacilities));
            using (System.IO.StreamReader file = new System.IO.StreamReader(facilitiyPath))
            {
                facilities = (ResultCodeFacilities)serializer.Deserialize(file);
            }

            foreach (var facility in facilities.Facility)
            {
                m_Facilities.Add(facility.Facility, facility);
            }
        }


        public void LoadCodes(Stream inputStream)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(SF.Table.ResultCodes));
            using (System.IO.StreamReader file = new System.IO.StreamReader(inputStream))
            {
                m_Codes = (ResultCodes)serializer.Deserialize(file);
            }
        }

        public void LoadCodes(string inputPath)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(SF.Table.ResultCodes));
            using (System.IO.StreamReader file = new System.IO.StreamReader(inputPath))
            {
                m_Codes = (ResultCodes)serializer.Deserialize(file);
            }
        }

        Result.SeverityType ToLocalSeverityType(SF.Table.Severity serverity)
        {
            switch (serverity)
            {
                case Severity.Success: return Result.SeverityType.Success;
                case Severity.Informational: return Result.SeverityType.Informational;
                case Severity.Warning: return Result.SeverityType.Warning;
                case Severity.Error:
                default:
                    return Result.SeverityType.Error;
            }
        }

        public void UpdateResultCode()
        {
            UpdateResultCode(m_Facilities, m_Codes);
        }

        void UpdateResultCode(Dictionary<string, ResultCodeFacility> Facilities, ResultCodes Codes)
        {
            var facility = m_Codes.Facility;
            var facilityID = m_Facilities[m_Codes.Facility];
            int facilityValue = Convert.ToInt32(facilityID.Value, 16);
            m_Codes.FacilityCode = facilityValue;

            Result codeValue = new Result();
            codeValue.Facility = facilityValue;
            codeValue.Custom = Codes.Custom;

            int codeIndex = 0;
            foreach (var codeItem in m_Codes.ResultCodeItem)
            {
                codeValue.Severity = ToLocalSeverityType(codeItem.Severity);
                codeValue.CodeIndex = codeIndex;
                codeIndex++;

                codeItem.ResultCode = codeValue;
            }
        }



        public void GenerateCPPHeaders(Stream outputStream)
        {
            var exporter = new ResultCodeExporterH();
            exporter.Export(m_Codes, outputStream);
        }

        public void GenerateCPPImplementation(Stream outputStream, string headerFileName)
        {
            var exporter = new ResultCodeExporterCPP(headerFileName);
            exporter.Export(m_Codes, outputStream);
        }

        public void GenerateSharp(Stream outputStream)
        {
            var exporter = new ResultCodeExporterSharp();
            exporter.Export(m_Codes, outputStream);
        }
    }
}

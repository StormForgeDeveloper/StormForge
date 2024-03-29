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
using System.Xml.Serialization;
using SF;
using SF.Table;

using System.IO;
using System.Diagnostics;
using Microsoft.Extensions.Primitives;


namespace SF
{
    public class ResultCodeExporterSharp
    {
        ResultCodes m_Codes;
        Stream m_OutputStream;



        public void Export(ResultCodes Codes, Stream outputStream)
        {
            StringBuilder output = new StringBuilder();

            m_Codes = Codes;
            m_OutputStream = outputStream;

            WritePreamble(output);
            WriteBody(output);
            WritePostamble(output);

            WriteToOutputHeader(output);
        }

        void WritePreamble(StringBuilder output)
        {
            output.Append("////////////////////////////////////////////////////////////////////////////////\n");
            output.Append("// \n");
            output.Append("// CopyRight (c) Kyungkun Ko\n");
            output.Append("// \n");
            output.Append("// Author : KyungKun Ko\n");
            output.Append("//\n");
            output.AppendFormat("// Description : Autogenerated file, {0}\n", m_Codes.Facility);
            output.Append("//\n");
            output.Append("////////////////////////////////////////////////////////////////////////////////\n");
            output.AppendLine("");
            output.AppendLine("using System;");
            output.AppendLine("");
            output.AppendLine("");
        }

        void WriteBody(StringBuilder output)
        {
            var facility = m_Codes.Facility;
            var facilityUpr = facility.ToUpper();

            output.AppendLine("namespace SF {");
            output.AppendLine("\tpublic partial struct ResultCode {");

            foreach (var codeItem in m_Codes.ResultCodeItem)
            {
                var codeValue = codeItem.ResultCode;

                string variableName = m_Codes.UseFacilityName ?
                    $"{Result.ServerityToDefineString(codeValue.Severity)}{facilityUpr}_{codeItem.CodeName.ToUpper()}"
                    : $"{Result.ServerityToDefineString(codeValue.Severity)}{codeItem.CodeName.ToUpper()}";


                // Description
                string strDefine = $"\t\tpublic static readonly Result {variableName} = ";
                output.AppendFormat("\n");
                output.AppendFormat("\t\t// {0} \n", string.IsNullOrEmpty(codeItem.Desc) ? "" : codeItem.Desc);

                // Constant definition
                output.Append($"\t\t public const int _{variableName} = (unchecked((int)0x{codeValue.Code:X8})); \n");

                // Result definition
                output.Append($"\t\tpublic static readonly Result {variableName} = new Result(_{variableName}); \n");
            }

            output.AppendLine("");
            output.AppendLine("\t}");
            output.AppendLine("}");
        }

        void WritePostamble(StringBuilder output)
        {
            output.AppendLine("");
            output.AppendLine("");
            output.AppendLine("");
        }

        void WriteToOutputHeader(StringBuilder output)
        {
            string outputString = output.ToString();
            var fileData = Encoding.UTF8.GetBytes(outputString);
            var preamble = Encoding.UTF8.GetPreamble();

            m_OutputStream.Write(preamble, 0, preamble.Length);
            m_OutputStream.Write(fileData, 0, fileData.Length);
        }
    }
}

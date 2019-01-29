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
using System.Xml.Serialization;
using SF;
using SF.Table;

using System.IO;
using System.Diagnostics;


namespace SFResultCodeCompiler
{
    class ResultCodeExporterXml
    {
        //List<ServerErrorTblServerErrorItem> m_itemList = new List<ServerErrorTblServerErrorItem>();


        //public void AddNewTable(ResultCodes Codes)
        //{
        //    var facility = Codes.Facility;
        //    var facilityUpr = facility.ToUpper();

        //    foreach (var codeItem in Codes.ResultCodeItem)
        //    {
        //        var xmlItem = new ServerErrorTblServerErrorItem();

        //        xmlItem.ErrorCode = codeItem.ResultCode.ID;
        //        string strDefine = "";
        //        if (Codes.UseFacilityName)
        //            strDefine = string.Format("{0}_{1}_{2}", ResultCode.ServerityToDefineString(codeItem.ResultCode.Severity), facilityUpr, codeItem.CodeName.ToUpper());
        //        else
        //            strDefine = string.Format("{0}_{1}", ResultCode.ServerityToDefineString(codeItem.ResultCode.Severity), codeItem.CodeName.ToUpper());
        //        xmlItem.Description = strDefine;

        //        m_itemList.Add(xmlItem);
        //    }
        //}

        //public void Export(string outPath)
        //{
        //    using (MemoryStream stream = new MemoryStream())
        //    using (var streamWriter = new StreamWriter(stream, System.Text.Encoding.UTF8))
        //    {
        //        ServerErrorTbl table = new ServerErrorTbl();

        //        table.ServerErrorItem = m_itemList.ToArray();

        //        XmlSerializer serializer = new XmlSerializer(typeof(ServerErrorTbl));
        //        serializer.Serialize(streamWriter, table);

        //        WriteToOutput(outPath, stream);
        //    }
        //}

        //void WriteToOutput(string outPath, MemoryStream output)
        //{
        //    outPath = PathTool.NormalizePath(outPath);// Path.Combine(outDir, string.Format("{0}.xml", m_FileName));

        //    FileUtil.WriteIfChanged(outPath, output.GetBuffer(), output.Length);
        //}
    }
}

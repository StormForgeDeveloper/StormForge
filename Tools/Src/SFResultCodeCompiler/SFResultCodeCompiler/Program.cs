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
using SF.Tool;
using SF.Table;

using System.IO;
using System.Diagnostics;




namespace SFResultCodeCompiler
{
    class Program
    {
        static int Main(string[] args)
        {
            ToolApplication.StartApplication();

            string outDir = AppConfig.GetValueString("out");
            string outDirSharp = AppConfig.GetValueString("outSharp");
            //string tableOutPath = AppConfig.GetValueString("tablepath");
            var inputPath = AppConfig.GetValueSet("in");
            string facilitiyPath = AppConfig.GetValueString("facility");
            if (inputPath == null)
            {
                Console.WriteLine("Empty input paramater:");
                return -1;
            }

            if (string.IsNullOrEmpty(outDir) && string.IsNullOrEmpty(outDirSharp))
            {
                Console.WriteLine("Empty outDir and outDirSharp paramater: at least one need to be specified");
                return -1;
            }

            //if (string.IsNullOrEmpty(tableOutPath))
            //{
            //    Console.WriteLine("Empty tableOutPath paramater:");
            //    return -1;
            //}


            if (string.IsNullOrEmpty(facilitiyPath))
            {
                Console.WriteLine("Empty facilities paramater:");
                return -1;
            }


            var resultCodeProcessor = new ResultCodeProcessor();
            try
            {
                resultCodeProcessor.LoadFacility(facilitiyPath);

                //var exporterXml = new ResultCodeExporterXml();

                foreach(var input in inputPath)
                {
                    resultCodeProcessor.LoadCodes(input.Key);

                    string inputName = Path.GetFileNameWithoutExtension(input.Key);
                    resultCodeProcessor.UpdateResultCode();

                    MemoryStream memoryStream;
                    string outPath;
                    if (!string.IsNullOrEmpty(outDir))
                    {
                        memoryStream = new MemoryStream();
                        resultCodeProcessor.GenerateCPPHeaders(memoryStream);
                        outPath = Path.Combine(outDir, string.Format("SF{0}.h", inputName));
                        FileUtil.WriteIfChanged(outPath, memoryStream.GetBuffer(), memoryStream.Length);
                    }

                    if(!string.IsNullOrEmpty(outDirSharp))
                    {
                        memoryStream = new MemoryStream();
                        resultCodeProcessor.GenerateSharp(memoryStream);
                        outPath = Path.Combine(outDirSharp, string.Format("SF{0}.cs", inputName));
                        FileUtil.WriteIfChanged(outPath, memoryStream.GetBuffer(), memoryStream.Length);
                    }
                }

            }
            catch (Exception exp)
            {
                Console.WriteLine("ERROR: Exception:{0}, at {1}", exp.Message, exp.StackTrace.ToString());
            }

            return 0;
        }
        


    }
}

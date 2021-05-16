////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Main program 
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Data;


using System.Reflection;

using SF;
using SF.Tool;

namespace ProtocolCompiler
{
    class Program
    {
        static ProtocolData m_protocolData;

        static string stm_CPPOut = "../../Test";
        static string stm_CSOut = "../../Test";
        static string stm_Out = "../../Test";
        static string strTempPath = "Temp/";


        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Need more parameter");
                Console.WriteLine("Usage : ProtocolCompiler.exe -out:OutputPath xmlFile1 [xmlFile2...]");
                return;
            }

            m_protocolData = new ProtocolData();
            List<Builder> builders = new List<Builder>();

            try
            {
                stm_CPPOut = AppConfig.GetValueString("dir");
                stm_Out = AppConfig.GetValueString("out", stm_Out);
                if (string.IsNullOrEmpty(stm_CPPOut))
                    stm_CPPOut = AppConfig.GetValueString("outCPP", stm_CPPOut);

                stm_CSOut = AppConfig.GetValueString("outSharp", stm_CSOut);

                var inputFile = AppConfig.GetValueString("in");
                if (!m_protocolData.LoadFile(inputFile))
                {
                    Console.WriteLine("XML Loading Failed: {0}", inputFile);
                    return;
                }

                // setup settings
                Dictionary<string, string> settings = new Dictionary<string, string>();
                settings["BasePath"] = strTempPath;

                // create builders
                var generators = AppConfig.GetValueSet("gen");
                foreach(var gen in generators)
                {
                    var generatorName = "ProtocolCompiler." + gen.Key;
                    var generatorType = Type.GetType(generatorName, false, true);
                    if(generatorType == null)
                    {
                        Console.WriteLine("Can't find generator {0}", generatorName);
                        continue;
                    }

                    var newGenerator = Activator.CreateInstance(generatorType, settings);
                    builders.Add(newGenerator as Builder);
                }

                ////builders.Add(new MessageIDBuilder(strTempPath));
                //builders.Add(new MessageClassBuilder(strTempPath));
                //builders.Add(new MessageParsingMapBuilder(strTempPath));
                //builders.Add(new MessageDebugBuilder(strTempPath));
                //builders.Add(new MessageAdapterCSharpBuilder(strTempPath));
                //builders.Add(new MessageIDCSharpBuilder(strTempPath));
                ////builders.Add(new MessageNetPolicyBuilder(strTempPath));
                //builders.Add(new MessageServerServiceBuilder(strTempPath));
                ////builders.Add(new MessageClusterNetPolicyBuilder(strTempPath));
                ////builders.Add(new MessageParserCSharpBuilder(strTempPath));
                ////builders.Add(new MessagePolicyCSharpBuilder(strTempPath));


                // Clean temp path
                if(Directory.Exists(strTempPath))
                    Directory.Delete(strTempPath, true);

                Directory.CreateDirectory(strTempPath);

                // Generate Server/Client Network Policy
                foreach (ProtocolXml.ProtocolsProtocolGroup group in m_protocolData.ProtocolGroupList)
                {
                    foreach (Builder builder in builders)
                    {
                        builder.Group = group;
                        builder.Build();
                    }
                }

                // copy only changed file
                string[] files = Directory.GetFiles(strTempPath, "*.*", SearchOption.AllDirectories);
                foreach (string file in files)
                {
                    CopyIfChanged(file);
                }
           }
            catch (System.IO.IOException sysex)
            {
                Console.WriteLine("System IO exception: {0}", sysex.Message, sysex.StackTrace.ToString());
            }
            catch (InvalidOperationException ioe)
            {
                Console.WriteLine("Invalid Operation: {0}: {1}",ioe.Message, ioe.StackTrace.ToString());
            }
            catch (SystemException ioe)
            {
                Console.WriteLine("System Exception: {0}: {1}", ioe.Message, ioe.StackTrace.ToString());
            }
            finally
            {
                Console.WriteLine("Work Done!");
            }
        }

        // copy if changed
        static void CopyIfChanged(string sourceFilePath)
        {
            string strTargetPath = stm_Out;
            switch (Path.GetExtension(sourceFilePath))
            {
                case ".cs":
                    strTargetPath = stm_CSOut;
                    break;
                case ".cpp":
                case ".h":
                case ".inl":
                    strTargetPath = stm_CPPOut;
                    break;
            }

            if(string.IsNullOrEmpty(strTargetPath))
            {
                throw new Exception(string.Format("Invalid target path for {0}", sourceFilePath));
            }

            string targetFilePath = Path.Combine(strTargetPath, Path.GetFileName(sourceFilePath));//sourceFilePath.Remove(0,strTempPath.Length);
            string targetDir = Path.GetDirectoryName(targetFilePath);

            Directory.CreateDirectory(targetDir);

            char[] sourceFileBuffer = new char[7 * 1024];
            int sourceFileReadSize = 0;
            char[] targetFileBuffer = new char[7 * 1024];
            int targetFileReadSize = 0;

            bool bIsMissMatched = false;
            using (FileStream source = new FileStream(sourceFilePath, FileMode.Open, FileAccess.Read, FileShare.Read))
            using (StreamReader sourceFile = new StreamReader(source, Encoding.UTF8))
            {
                try
                {
                    using (FileStream target = new FileStream(targetFilePath, FileMode.Open, FileAccess.Read, FileShare.Read))
                    using (StreamReader targetFile = new StreamReader(target, Encoding.UTF8))
                    {
                        while (!bIsMissMatched)
                        {
                            sourceFileReadSize = sourceFile.Read(sourceFileBuffer, 0, sourceFileBuffer.Length);
                            targetFileReadSize = targetFile.Read(targetFileBuffer, 0, targetFileBuffer.Length);
                            if (targetFileReadSize != sourceFileReadSize)
                            {
                                bIsMissMatched = true;
                                break;
                            }
                            else if (targetFileReadSize == 0)
                            {
                                break;
                            }

                            int iChar = 0;
                            for (iChar = 0; iChar < sourceFileReadSize; iChar++)
                            {
                                if (sourceFileBuffer[iChar] != targetFileBuffer[iChar])
                                {
                                    bIsMissMatched = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                catch (System.IO.IOException)
                {
                    // maybe file not exist, create new one
                    bIsMissMatched = true;
                }
            }

            if( !bIsMissMatched )
                return;

            Console.WriteLine( "Copying : " + targetFilePath );

            File.Copy(sourceFilePath, targetFilePath, true);

            // Delete temp file
            File.Delete(sourceFilePath);
        }
   
    }
}

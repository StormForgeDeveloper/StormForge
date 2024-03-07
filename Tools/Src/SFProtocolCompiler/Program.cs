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

        static string stm_Out = "Out/";
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
                stm_Out = AppConfig.GetValueString("out", stm_Out);

                var typeDefs = AppConfig.GetValueSet("TypeDef");
                if (typeDefs != null)
                {
                    var typeLoader = new ProtocolTypeLoader();
                    foreach (var typeDef in typeDefs)
                    {
                        typeLoader.LoadFile(typeDef.Key);
                    }
                }

                var inputFile = AppConfig.GetValueString("in");
                if (!m_protocolData.LoadFile(inputFile))
                {
                    Console.WriteLine("XML Loading Failed: {0}", inputFile);
                    return;
                }

                // setup settings
                Dictionary<string, string> settings = new Dictionary<string, string>();
                settings["BasePath"] = stm_Out;
                settings["CSharpProtocolNamespace"] = AppConfig.GetValueString("CSharpProtocolNamespace");

                // create builders
                var generators = AppConfig.GetValueSet("gen");
                if (generators != null)
                {
                    foreach (var gen in generators)
                    {
                        var generatorName = "ProtocolCompiler." + gen.Key;
                        var generatorType = Type.GetType(generatorName, false, true);
                        if (generatorType == null)
                        {
                            Console.WriteLine("Can't find generator {0}", generatorName);
                            continue;
                        }

                        var newGenerator = Activator.CreateInstance(generatorType, settings);
                        builders.Add(newGenerator as Builder);
                    }
                }

                // Clean temp path
                if (Directory.Exists(strTempPath))
                    Directory.Delete(strTempPath, true);

                Directory.CreateDirectory(strTempPath);

                // Generate Server/Client Network Policy
                foreach (ProtocolXml.ProtocolsProtocolGroup group in m_protocolData.ProtocolGroupList)
                {
                    foreach (Builder builder in builders)
                    {
                        Console.WriteLine($"Running builder:{builder.GetType().Name}");

                        builder.Group = group;
                        builder.Build();
                    }
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

    }
}

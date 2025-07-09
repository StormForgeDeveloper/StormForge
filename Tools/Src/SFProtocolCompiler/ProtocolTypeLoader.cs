////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol type data loader
//
////////////////////////////////////////////////////////////////////////////////




using SF;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Drawing.Drawing2D;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;

namespace ProtocolCompiler
{
    class ProtocolTypeLoader
    {
        public bool bPrintDebugInfo { get; set; } = false;

        public ProtocolTypeLoader()
        {
        }

        // Load Protocol XML and merge to current protocol group
        public bool LoadFile(string strFileName)
        {
            try
            {
                TextReader reader = new StreamReader(strFileName);
                XmlSerializer serializer = new XmlSerializer(typeof(ProtocolXml.ProtocolTypes));
                ProtocolXml.ProtocolTypes protocolTypes = (ProtocolXml.ProtocolTypes)serializer.Deserialize(reader);
                reader.Close();

                foreach (var itDataType in protocolTypes.DataType)
                {
                    if (bPrintDebugInfo)
                    {
                        System.Console.WriteLine($"New Type: {itDataType.TypeName}, cpp:{itDataType.CppTypeName}, c#:{itDataType.CSharpTypeName}");
                    }

                    SystemTypeInfo.AddTypeInfo(itDataType);
                }
            }
            catch (XmlException xe)
            {
                Console.WriteLine("XML Parse Error: " + xe.Message);
                return false;

            }
            catch (InvalidOperationException ioe)
            {
                Console.WriteLine("XML Serialization Error: " + ioe.Message);

                return false;
            }
            catch (SystemException se)
            {
                Console.WriteLine("System Error: " + se.Message);
                return false;
            }

            return true;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Protocol type data loader
//
////////////////////////////////////////////////////////////////////////////////




using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Data;
using System.Collections;
using SF;

namespace ProtocolCompiler
{
    class ProtocolTypeLoader
    {
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

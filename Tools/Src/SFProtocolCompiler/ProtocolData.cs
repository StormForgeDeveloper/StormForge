////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
// Date : 01/03/2013
//
// Description : Protocol data manager
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




namespace ProtocolCompiler
{
    class ProtocolData
    {
        // list of protocol group
        ProtocolXml.ProtocolsProtocolGroup[] m_protocolList = {};

        public ProtocolData()
        {
            //m_protocolList = new ArrayList();
        }

        public ProtocolXml.ProtocolsProtocolGroup[] ProtocolGroupList
        {
            get
            {
                return this.m_protocolList;
            }
        }

        public ProtocolXml.ProtocolsProtocolGroup this[int index]
        {
            get
            {
                return m_protocolList[index];
            }
        }

        // Load Protocol XML and merge to current protocol group
        public bool LoadFile(string strFileName)
        {
            try
            {
                TextReader reader = new StreamReader(strFileName);
                XmlSerializer serializer = new XmlSerializer(typeof(ProtocolXml.Protocols));
                ProtocolXml.Protocols proto = (ProtocolXml.Protocols)serializer.Deserialize(reader);
                reader.Close();

                ArrayList arrayList = new ArrayList(m_protocolList.Length);
                foreach (ProtocolXml.ProtocolsProtocolGroup protoGrp in m_protocolList)
                {
                    arrayList.Add(protoGrp);
                }

                foreach (ProtocolXml.ProtocolsProtocolGroup protocolGroup in proto.ProtocolGroup)
                {
                    arrayList.Add(protocolGroup);
                }

                m_protocolList = new ProtocolXml.ProtocolsProtocolGroup[arrayList.Count];
                arrayList.CopyTo(m_protocolList);
                //m_protocolList = (ProtocolXml.ProtocolsProtocolGroup[])arrayList.ToArray();
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

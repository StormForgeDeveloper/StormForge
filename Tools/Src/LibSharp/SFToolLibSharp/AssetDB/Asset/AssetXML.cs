////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .xml files
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.Tool.Schema;
using System.Xml;
using System.Xml.Serialization;

namespace SF.Asset
{
    // Data asset xml
    public abstract class AssetXML : AssetFile
    {
        public AssetXML()
            : this("empty.xml")
        {
        }

        public AssetXML(string sourcePath)
            : base(sourcePath)
        {
            //ConvertableToTypes.Add(".obj");
        }

        public T LoadXML<T>()
        {
            using (System.IO.StreamReader file = new System.IO.StreamReader(SourceFilePath))
            {
                XmlSerializer serializer = new XmlSerializer(typeof(T));
                return (T)serializer.Deserialize(file);
            }
        }
        public T LoadXML<T>(Stream stream)
        {
            using (System.IO.StreamReader file = new System.IO.StreamReader(stream))
            {
                XmlSerializer serializer = new XmlSerializer(typeof(T));
                return (T)serializer.Deserialize(file);
            }
        }

    }
}

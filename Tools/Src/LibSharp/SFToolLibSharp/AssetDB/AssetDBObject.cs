////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset database
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Text;
using SF.Tool;
using SF.Tool.Schema;

namespace SF.Asset
{
    public abstract class AssetDBObject
    {
        public string Name { get; internal set; }

        // DBItem node
        public Asset DBItem;

        // 
        //public abstract void Import(Asset asset, Stream inputStream);
    }

}

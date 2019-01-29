////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset 
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SF.Tool.Schema;

namespace SF.Asset
{
    /// <summary>
    /// File asset. No importer
    /// </summary>
    public abstract class AssetFile : Asset
    {
        public AssetFile(string sourcePath)
            : base(Path.GetFileName(sourcePath), sourcePath, Path.GetExtension(sourcePath).ToLower())
        {
        }
    }
    
}

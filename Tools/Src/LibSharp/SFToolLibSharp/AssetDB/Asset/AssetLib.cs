////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .lib files
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
    // Data asset .lib
    public class AssetLib : AssetFile
    {
        public AssetLib()
            : this("empty.lib")
        {
        }

        public AssetLib(string sourcePath)
            : base(sourcePath)
        {
        }
    }


}

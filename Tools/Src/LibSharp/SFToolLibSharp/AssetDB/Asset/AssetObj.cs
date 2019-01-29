////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .obj files
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
    // Data asset obj
    public class AssetObj : AssetFile
    {
        public AssetObj()
            : this("empty.obj")
        {
        }

        public AssetObj(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".exe");
            ConvertableToTypes.Add(".lib");
            //TargetTypes.Add(".dll");
        }
    }

}

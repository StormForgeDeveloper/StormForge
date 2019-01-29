////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .cs files
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
    // Data asset cs
    public class AssetCS : AssetFile
    {
        public AssetCS()
            : this("empty.cs")
        {
        }

        public AssetCS(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".obj");
        }
    }


}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .sln files
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
    // Data asset VS solution
    public class AssetVCSolution : AssetFile
    {
        public AssetVCSolution()
            : this("empty.sln")
        {
        }

        public AssetVCSolution(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".vcxproj");
            ConvertableToTypes.Add(".csproj");
        }
    }

}

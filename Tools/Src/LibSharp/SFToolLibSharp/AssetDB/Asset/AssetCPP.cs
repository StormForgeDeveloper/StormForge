////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .cpp files
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
    // Data asset cpp
    public class AssetCPP : AssetFile
    {
        public AssetCPP()
            : this("empty.cpp")
        {
        }

        public AssetCPP(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".obj");
        }
    }


}

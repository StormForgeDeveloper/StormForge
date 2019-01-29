////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .c files
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
    // Data asset c
    public class AssetC : AssetFile
    {
        public AssetC()
            : this("empty.c")
        {
        }

        public AssetC(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".obj");
        }
    }

}

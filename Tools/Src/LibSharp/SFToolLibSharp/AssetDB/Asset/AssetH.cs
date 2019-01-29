////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset .h files
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
    // Data asset .h
    public class AssetH : AssetFile
    {
        public AssetH()
            : this("empty.h")
        {
        }

        public AssetH(string sourcePath)
            : base(sourcePath)
        {
        }
    }

    public class AssetInl : AssetFile
    {
        public AssetInl()
            : base("empty.inl")
        {
        }

        public AssetInl(string sourcePath)
            : base(sourcePath)
        {
        }
    }

    public class AssetDef : AssetFile
    {
        public AssetDef()
            : base("empty.def")
        {
        }

        public AssetDef(string sourcePath)
            : base(sourcePath)
        {
        }
    }

}

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
    // Data asset VCCs project
    public class AssetVCCSProject : AssetFile
    {
        public AssetVCCSProject()
            : this("empty.csproj")
        {
        }

        public AssetVCCSProject(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".cs");
            ConvertableToTypes.Add(".xml");
            ConvertableToTypes.Add(".bin");
        }
    }

}

////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset VC prject
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
    // Data asset VC project
    public class AssetVCProject : AssetFile
    {
        public AssetVCProject()
            : this("empty.vcxproj")
        {
        }

        public AssetVCProject(string sourcePath)
            : base(sourcePath)
        {
            ConvertableToTypes.Add(".h");
            ConvertableToTypes.Add(".hpp");
            ConvertableToTypes.Add(".inl");
            ConvertableToTypes.Add(".def");
            ConvertableToTypes.Add(".c");
            ConvertableToTypes.Add(".cpp");
            ConvertableToTypes.Add(".xml");
            ConvertableToTypes.Add(".bin");
        }
    }

}
